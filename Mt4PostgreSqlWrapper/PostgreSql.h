#ifndef POSTGRESQL_H
#define POSTGRESQL_H

#include <iostream>
#include <sstream>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "libpq-fe.h"
#include "Common.h"
#include "Logger.h"

const int MAX_CONNECT_ATTEMPTS = 3;
const int SLEEP_CONNECT_FAILED = 1000;

class PostgreSql
{
private:
    PGconn * connection = NULL;
    std::wstring connection_string = L"";
    std::string _connection_string = "";

    PGresult * result = NULL;
    int num_rows = 0;
    int num_fields = 0;
    std::wstring affected_rows = L"";

    std::wstring last_error = L"";

    Logger * logger = NULL;

public:
    PostgreSql(Logger * const logger);
    ~PostgreSql();

    const std::wstring AffectedRows();
    const bool CheckConnection();
    void ClearResult();
    const int ClientVersion();
    void Close();
    const bool Connect(const std::wstring connection_string);
    const bool FetchField(wchar_t * const field, const int row_num, const int field_num);
    const std::wstring GetFieldList();
    const std::wstring GetLastError();
    const int NumFields();
    const int NumRows();
    const bool Query(const std::wstring query, const bool silence_conflict = false);
    const int ServerVersion();
};

namespace {
    inline PostgreSql * const GetPostgreSql(const int wrapper) {
        return reinterpret_cast<PostgreSql * const>(wrapper);
    }
}

//
// DLLAPI
//
DLLAPI void DllPostgreSqlDestroy(const int wrapper);
DLLAPI const int DllPostgreSqlInit(const int logger);
DLLAPI void DllPostgreSqlAffectedRows(const int wrapper, wchar_t * const affected_rows);
DLLAPI const bool DllPostgreSqlCheckConnection(const int wrapper);
DLLAPI void DllPostgreSqlClearResult(const int wrapper);
DLLAPI const int DllPostgreSqlClientVersion(const int wrapper);
DLLAPI void DllPostgreSqlClose(const int wrapper);
DLLAPI const bool DllPostgreSqlConnect(const int wrapper, const wchar_t * const connection_string);
DLLAPI const bool DllPostgreSqlFetchField(const int wrapper, wchar_t * const field, const int row_num, const int field_num);
DLLAPI void DllPostgreSqlGetFieldList(const int wrapper, wchar_t * const field_list);
DLLAPI void DllPostgreSqlGetLastError(const int wrapper, wchar_t * const last_error);
DLLAPI const int DllPostgreSqlNumFields(const int wrapper);
DLLAPI const int DllPostgreSqlNumRows(const int wrapper);
DLLAPI const bool DllPostgreSqlQuery(const int wrapper, const wchar_t * const query, const bool silence_conflict = false);
DLLAPI const int DllPostgreSqlServerVersion(const int wrapper);
DLLAPI const wchar_t * const DllPostgreSqlWrapperVersion();

#endif