/*
    Copyright 2015-2018 Clément Gallet <clement.gallet@ens-lyon.org>

    This file is part of libTAS.

    libTAS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libTAS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libTAS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "localewrappers.h"
#include "logging.h"
#include "hook.h"

namespace libtas {

DEFINE_ORIG_POINTER(setlocale)
DEFINE_ORIG_POINTER(getenv)

/* Override */ char *setlocale (int category, const char *locale) throw()
{
    // static char enlocale[] = "en_US.utf8";
    debuglog(LCF_LOCALE, __func__, " called with category ", category, " and locale ", locale);
    LINK_NAMESPACE_GLOBAL(setlocale);
    char* ret = orig::setlocale(category, locale);
    debuglog(LCF_LOCALE, "  returning ", ret);
    return ret;
}

char *getenv (const char *name) throw()
{
    static char lang_en[] = "en_US.utf8";
    debuglog(LCF_LOCALE, __func__, " called with name ", name);
    LINK_NAMESPACE_GLOBAL(getenv);
    if (0 == strncmp(name, "LANG", 4)) {
        return lang_en;
    }
    char* ret = orig::getenv(name);
    debuglog(LCF_LOCALE, "  returning ", ret);

    return ret;
}

}
