
#include "worker.h"
#include "cppcodebuilder.h"

Worker::Worker(CppCodeBuilder* builder)
    : m_pBuildData(builder)
{
}

void Worker::process()
{
    using dllGetModelsSize       = std::size_t(__cdecl*)();
    using dllGetModel            = Model * (__cdecl*)(int index);
    using dllEntryPoint          = bool(__cdecl*)();
    using dllGetMessagesSize     = std::size_t(__cdecl*)();
    using dllGetMessage          = const char* (__cdecl*)(int index);
    using dllGetMessageBoxesSize = std::size_t(__cdecl*)();
    using dllGetMessageBoxTitle  = const char* (__cdecl*)(int index);
    using dllGetMessageBoxText   = const char* (__cdecl*)(int index);

    dllEntryPoint           entryPoint          = (dllEntryPoint)(m_pBuildData->m_dll.resolve("entry_point"));
    dllGetModelsSize        getModelsSize       = (dllGetModelsSize)(m_pBuildData->m_dll.resolve("get_models_size"));
    dllGetModel             getModel            = (dllGetModel)(m_pBuildData->m_dll.resolve("get_model"));
    dllGetMessagesSize      getMessagesSize     = (dllGetMessagesSize)(m_pBuildData->m_dll.resolve("get_messages_size"));
    dllGetMessage           getMessage          = (dllGetMessage)(m_pBuildData->m_dll.resolve("get_message"));
    dllGetMessageBoxesSize  getMessageBoxesSize = (dllGetMessageBoxesSize)(m_pBuildData->m_dll.resolve("get_messageBoxes_size"));
    dllGetMessageBoxTitle   getMessageBoxTitle  = (dllGetMessageBoxTitle)(m_pBuildData->m_dll.resolve("get_messageBoxTitle"));
    dllGetMessageBoxText    getMessageBoxText   = (dllGetMessageBoxText)(m_pBuildData->m_dll.resolve("get_messageBoxText"));

    if (entryPoint == nullptr || getModelsSize == nullptr || getModel == nullptr ||
        getMessagesSize == nullptr || getMessage == nullptr || getMessageBoxesSize == nullptr ||
        getMessageBoxTitle == nullptr || getMessageBoxText == nullptr)
    {
        emit finished(false);
    }
    else
    {
        m_pBuildData->m_objectsCollection.clear();
        m_pBuildData->m_messages.clear();
        m_pBuildData->m_messageBoxes.clear();

        bool isOk = false;
        isOk = entryPoint();

        std::size_t messagesSize = 0;
        messagesSize = getMessagesSize();
        for (std::size_t i = 0; i < messagesSize; ++i)
        {
            m_pBuildData->m_messages.push_back(QString(getMessage(i)));
        }

        std::size_t messageBoxesSize = 0;
        messageBoxesSize = getMessageBoxesSize();
        for (std::size_t i = 0; i < messageBoxesSize; ++i)
        {
            m_pBuildData->m_messageBoxes.push_back({QString(getMessageBoxTitle(i)),
                                                    QString(getMessageBoxText(i))});
        }

        std::size_t modelsSize = 0;
        modelsSize = getModelsSize();
        for (std::size_t i = 0; i < modelsSize; ++i)
        {
            m_pBuildData->m_objectsCollection.push_back(*getModel(i));
        }

        emit finished(isOk);
    }
}