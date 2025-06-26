#include <jni.h>
#include <string>
#include "Game.h"
#include "FieldedAreaGame.h"
#include "TicTacToe.h"
#include "Tags.h"
#include "Sudoku.h"

std::unique_ptr<Game> m_activeGame;

jobject cppOptionalToJava(JNIEnv *env, std::optional<uint8_t> cppOptional) {
    jclass optionalClass = env->FindClass("java/util/Optional");
    jmethodID ofNullable = env->GetStaticMethodID(
            optionalClass,
            "ofNullable",
            "(Ljava/lang/Object;)Ljava/util/Optional;"
    );
    jmethodID empty = env->GetStaticMethodID(optionalClass, "empty", "()Ljava/util/Optional;");

    if (cppOptional.has_value()) {
        jclass integerClass = env->FindClass("java/lang/Integer");
        jmethodID valueOf = env->GetStaticMethodID(
                integerClass,
                "valueOf",
                "(I)Ljava/lang/Integer;"
        );

        jobject javaInt = env->CallStaticObjectMethod(
                integerClass,
                valueOf,
                (jint) cppOptional.value()
        );

        return env->CallStaticObjectMethod(optionalClass, ofNullable, javaInt);
    } else {
        return env->CallStaticObjectMethod(optionalClass, empty);
    }
}

std::optional<int> javaOptionalToCpp(JNIEnv *env, jobject javaOptional) {
    if (javaOptional == nullptr) {
        return std::nullopt;
    }

    jclass optionalClass = env->GetObjectClass(javaOptional);
    jmethodID isPresent = env->GetMethodID(optionalClass, "isPresent", "()Z");
    jmethodID get = env->GetMethodID(optionalClass, "get", "()Ljava/lang/Object;");

    jboolean present = env->CallBooleanMethod(javaOptional, isPresent);
    if (!present) {
        return std::nullopt;
    }

    jobject javaInt = env->CallObjectMethod(javaOptional, get);
    jclass integerClass = env->GetObjectClass(javaInt);
    jmethodID intValue = env->GetMethodID(integerClass, "intValue", "()I");
    jint value = env->CallIntMethod(javaInt, intValue);

    return std::optional<int>(value);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_gamesapplication_MainActivity_setGame(JNIEnv *env, jobject thiz, jstring name) {
    const char *gameName = env->GetStringUTFChars(name, nullptr);
    m_activeGame.reset();

    if (strcmp(gameName, "TicTacToe") == 0) {
        m_activeGame = std::make_unique<TicTacToe>();
    } else if (strcmp(gameName, "Tags") == 0) {
        m_activeGame = std::make_unique<Tags>();
    } else {
        m_activeGame = std::make_unique<Sudoku>();
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_gamesapplication_GameInformationPanel_sendPlayerName(JNIEnv *env, jobject thiz,
                                                                      jstring name) {
    const char *cstr = env->GetStringUTFChars(name, nullptr);
    std::string nameCpp(cstr);
    m_activeGame->SetName(nameCpp);
}
extern "C"
JNIEXPORT jintArray JNICALL
Java_com_example_gamesapplication_GameArea_getUserArea(JNIEnv *env, jobject thiz) {
    std::vector<uint8_t> data = dynamic_cast<FieldedAreaGame *>(m_activeGame.get())->GetUserArea();
    jintArray result = env->NewIntArray(data.size());
    if (result == nullptr) {
        return nullptr;
    }
    jint *tempArray = new jint[data.size()];
    for (int i = 0; i < data.size(); i++) {
        tempArray[i] = static_cast<jint>(data[i]);
    }
    env->SetIntArrayRegion(result, 0, data.size(), tempArray);
    delete[] tempArray;

    return result;
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_example_gamesapplication_GameArea_sendData(JNIEnv *env, jobject thiz, jint index,
                                                    jobject value) {
    std::optional<uint8_t> val = javaOptionalToCpp(env, value);
    std::optional<uint8_t> result = m_activeGame->Step(index, val);

    return cppOptionalToJava(env, result);
}
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_gamesapplication_GameInformationPanel_getWinnerInformation(JNIEnv *env,
                                                                            jobject thiz) {
    std::string data;
    data = m_activeGame->GetWinnerInformation();
    return env->NewStringUTF(data.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_example_gamesapplication_MainActivity_restart(JNIEnv *env, jobject thiz) {
    m_activeGame->RestartGame();
}