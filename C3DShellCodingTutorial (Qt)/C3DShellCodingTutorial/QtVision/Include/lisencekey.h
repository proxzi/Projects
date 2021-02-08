#ifndef __LISENCEKEY_H
#define __LISENCEKEY_H

#include <string>

#ifdef VSN_OS_WIN
static const std::string strKey = "MosPolytech2020.2020011520201231.[cnv][mdl][slv][vsn][bsh]";
static const std::string strSignature = "AW3FSVT2UOVSsLN1/jaPC0BCknN7KQyQXZ8jl1ogNpmlIbCQThcgQ1QNwvzKI+Aqk1oYjVsuQQudrcsHKJ9ERw==";
#else
static const std::string strKey = "MosPolytech2020.2020011520201231.[cnv][mdl][slv][vsn][bsh];
static const std::string strSignature = "AW3FSVT2UOVSsLN1/jaPC0BCknN7KQyQXZ8jl1ogNpmlIbCQThcgQ1QNwvzKI+Aqk1oYjVsuQQudrcsHKJ9ERw==";
#endif

#endif // __LISENCEKEY_H
