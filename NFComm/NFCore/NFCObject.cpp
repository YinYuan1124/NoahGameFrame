// -------------------------------------------------------------------------
//    @FileName         :    NFCObject.cpp
//    @Author           :    LvSheng.Huang
//    @Date             :    2012-03-01
//    @Module           :    NFCObject
//
// -------------------------------------------------------------------------

#include "NFCObject.h"
#include "NFCRecordManager.h"
#include "NFCHeartBeatManager.h"
#include "NFCPropertyManager.h"
#include "NFCComponentManager.h"

NFCObject::NFCObject(const NFIDENTID& self, NFIPluginManager* pLuginManager)
{
    mSelf = self;
    m_pPluginManager = pLuginManager;

    m_pRecordManager = new NFCRecordManager(mSelf);
    m_pHeartBeatManager = new NFCHeartBeatManager(mSelf);
    m_pPropertyManager = new NFCPropertyManager(mSelf);
    m_pComponentManager = new NFCComponentManager(mSelf);
}

NFCObject::~NFCObject()
{
    delete m_pComponentManager;
    delete m_pPropertyManager;
    delete m_pRecordManager;
    delete m_pHeartBeatManager;
}

bool NFCObject::Init()
{
    return true;
}

bool NFCObject::Shut()
{

    return true;
}

bool NFCObject::Execute(const float fLastTime, const float fAllTime)
{
    //循环的心跳中，可能删除自己
    GetHeartBeatManager()->Execute(fLastTime, fAllTime);
    GetComponentManager()->Execute(fLastTime, fAllTime);

    return true;
}

bool NFCObject::AddHeartBeat(const std::string& strHeartBeatName, const HEART_BEAT_FUNCTOR_PTR& cb, const NFIValueList& var, const float fTime, const int nCount)
{
    return GetHeartBeatManager()->AddHeartBeat(mSelf , strHeartBeatName, cb, var, fTime, nCount);
}

bool NFCObject::FindHeartBeat(const std::string& strHeartBeatName)
{
    return GetHeartBeatManager()->Exist(strHeartBeatName);
}

bool NFCObject::RemoveHeartBeat(const std::string& strHeartBeatName)
{
    return GetHeartBeatManager()->RemoveHeartBeat(strHeartBeatName);
}

bool NFCObject::AddRecordCallBack(const std::string& strRecordName, const RECORD_EVENT_FUNCTOR_PTR& cb)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        pRecord->AddRecordHook(cb);

        return true;
    }

    return false;
}

bool NFCObject::AddPropertyCallBack(const std::string& strCriticalName, const PROPERTY_EVENT_FUNCTOR_PTR& cb)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strCriticalName);
    if (pProperty)
    {
        pProperty->RegisterCallback(cb, NFCValueList());

        return true;
    }

    return false;
}

bool NFCObject::FindProperty(const std::string& strPropertyName)
{
    if (GetPropertyManager()->GetElement(strPropertyName))
    {
        return true;
    }

    return false;
}

bool NFCObject::SetPropertyInt(const std::string& strPropertyName, const int nValue)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {
        pProperty->SetInt(nValue);

        return true;
    }

    return false;
}

bool NFCObject::SetPropertyFloat(const std::string& strPropertyName,  const float fValue)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {
        pProperty->SetFloat(fValue);

        return true;
    }


    return false;
}

bool NFCObject::SetPropertyDouble(const std::string& strPropertyName, const double dwValue)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {
        pProperty->SetDouble(dwValue);

        return true;
    }


    return false;
}

bool NFCObject::SetPropertyString(const std::string& strPropertyName, const std::string& strValue)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {
        pProperty->SetString(strValue);

        return true;
    }

    return false;
}

bool NFCObject::SetPropertyObject(const std::string& strPropertyName, const NFIDENTID& obj)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {
        pProperty->SetObject(obj);

        return true;
    }

    return false;
}

int NFCObject::QueryPropertyInt(const std::string& strPropertyName)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {

        return pProperty->QueryInt();
    }

    return -1;
}

float NFCObject::QueryPropertyFloat(const std::string& strPropertyName)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {

        return pProperty->QueryFloat();
    }

    return 0.0f;
}

double NFCObject::QueryPropertyDouble(const std::string& strPropertyName)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {

        return pProperty->QueryDouble();
    }

    return 0.0;
}

const std::string& NFCObject::QueryPropertyString(const std::string& strPropertyName)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {

        return pProperty->QueryString();
    }

    return NULL_STR;
}

NFIDENTID NFCObject::QueryPropertyObject(const std::string& strPropertyName)
{
    NFIProperty* pProperty = GetPropertyManager()->GetElement(strPropertyName);
    if (pProperty)
    {

        return pProperty->QueryObject();
    }

    return 0;
}

bool NFCObject::FindRecord(const std::string& strRecordName)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return true;
    }

    return false;
}

bool NFCObject::SetRecordInt(const std::string& strRecordName, const int nRow, const int nCol, const int nValue)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return SetRecordInt(pRecord, strRecordName, nRow, nCol, nValue);
    }

    return false;
}

bool NFCObject::SetRecordInt(NFIRecord* pRecord, const std::string& strRecordName, const int nRow, const int nCol, const int nValue)
{
    if (pRecord)
    {
        return pRecord->SetInt(nRow, nCol, nValue);
    }

    return false;
}

bool NFCObject::SetRecordFloat(const std::string& strRecordName, const int nRow, const int nCol, const float fValue)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return SetRecordFloat(pRecord, strRecordName, nRow, nCol, fValue);
    }

    return false;
}

bool NFCObject::SetRecordFloat(NFIRecord* pRecord, const std::string& strRecordName, const int nRow, const int nCol, const float fValue)
{
    if (pRecord)
    {
        return pRecord->SetFloat(nRow, nCol, fValue);
    }

    return false;
}

bool NFCObject::SetRecordDouble(const std::string& strRecordName, const int nRow, const int nCol, const double dwValue)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return SetRecordDouble(pRecord, strRecordName, nRow, nCol, dwValue);
    }

    return false;
}

bool NFCObject::SetRecordDouble(NFIRecord* pRecord, const std::string& strRecordName, const int nRow, const int nCol, const double dwValue)
{
    if (pRecord)
    {
        return pRecord->SetDouble(nRow, nCol, dwValue);
    }

    return false;
}

bool NFCObject::SetRecordString(const std::string& strRecordName, const int nRow, const int nCol, const std::string& strValue)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return SetRecordString(pRecord, strRecordName, nRow, nCol, strValue);
    }

    return false;
}

bool NFCObject::SetRecordString(NFIRecord* pRecord, const std::string& strRecordName, const int nRow, const int nCol, const std::string& strValue)
{
    if (pRecord)
    {
        return pRecord->SetString(nRow, nCol, strValue.c_str());
    }

    return false;
}

bool NFCObject::SetRecordObject(const std::string& strRecordName, const int nRow, const int nCol, const NFIDENTID& obj)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return SetRecordObject(pRecord, strRecordName, nRow, nCol, obj);
    }

    return false;
}

bool NFCObject::SetRecordObject(NFIRecord* pRecord, const std::string& strRecordName, const int nRow, const int nCol, const NFIDENTID& obj)
{
    if (pRecord)
    {
        return pRecord->SetObject(nRow, nCol, obj);
    }

    return false;
}

int NFCObject::QueryRecordInt(const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return QueryRecordInt(pRecord, strRecordName, nRow, nCol);
    }

    return 0;
}

int NFCObject::QueryRecordInt(NFIRecord* pRecord, const std::string& strRecordName, const int nRow, const int nCol)
{
    if (pRecord)
    {
        return pRecord->QueryInt(nRow, nCol);
    }

    return 0;
}

float NFCObject::QueryRecordFloat(const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return QueryRecordFloat(pRecord, strRecordName, nRow, nCol);
    }

    return 0.0f;
}

float NFCObject::QueryRecordFloat(NFIRecord* pRecord, const std::string& strPropertyName, const int nRow, const int nCol)
{
    if (pRecord)
    {
        return pRecord->QueryFloat(nRow, nCol);
    }

    return 0.0f;
}

double NFCObject::QueryRecordDouble(const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return QueryRecordDouble(pRecord, strRecordName, nRow, nCol);
    }

    return 0.0;
}

double NFCObject::QueryRecordDouble(NFIRecord* pRecord, const std::string& strPropertyName, const int nRow, const int nCol)
{
    if (pRecord)
    {
        return pRecord->QueryDouble(nRow, nCol);
    }

    return 0.0;
}

const std::string& NFCObject::QueryRecordString(const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return QueryRecordString(pRecord, strRecordName, nRow, nCol);
    }

    return NULL_STR;
}

const std::string& NFCObject::QueryRecordString(NFIRecord* pRecord, const std::string& strPropertyName, const int nRow, const int nCol)
{
    if (pRecord)
    {
        return pRecord->QueryString(nRow, nCol);
    }

    return NULL_STR;
}

NFIDENTID NFCObject::QueryRecordObject(const std::string& strRecordName, const int nRow, const int nCol)
{
    NFIRecord* pRecord = GetRecordManager()->GetElement(strRecordName);
    if (pRecord)
    {
        return QueryRecordObject(pRecord, strRecordName, nRow, nCol);
    }

    return 0;
}

NFIDENTID NFCObject::QueryRecordObject(NFIRecord* pRecord, const std::string& strPropertyName, const int nRow, const int nCol)
{
    if (pRecord)
    {
        return pRecord->QueryObject(nRow, nCol);
    }

    return 0;
}

NFIRecordManager* NFCObject::GetRecordManager()
{
    return m_pRecordManager;
}

NFIHeartBeatManager* NFCObject::GetHeartBeatManager()
{
    return m_pHeartBeatManager;
}

NFIPropertyManager* NFCObject::GetPropertyManager()
{
    return m_pPropertyManager;
}

NFIDENTID NFCObject::Self()
{
    return mSelf;
}

NFIComponentManager* NFCObject::GetComponentManager()
{
    return m_pComponentManager;
}

NFIComponent* NFCObject::AddComponent( const std::string& strComponentName, const std::string& strLanguageName )
{
    return m_pComponentManager->AddComponent(strComponentName, strLanguageName);
}

NFIComponent* NFCObject::FindComponent( const std::string& strComponentName )
{
    return m_pComponentManager->FindComponent(strComponentName);
}
