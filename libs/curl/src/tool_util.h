#ifndef HEADER_CURL_TOOL_UTIL_H
#define HEADER_CURL_TOOL_UTIL_H
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 * SPDX-License-Identifier: curl
 *
 ***************************************************************************/
#include "tool_setup.h"

/**
 * Return timeval of the REALTIME clock.
 */
struct timeval tvrealnow(void);

/* Case insensitive comparison support. */
int struplocompare(const char *p1, const char *p2);
int struplocompare4sort(const void *p1, const void *p2);

#if defined(_WIN32) && !defined(UNDER_CE)
FILE *tool_execpath(const char *filename, char **pathp);
#endif

#endif /* HEADER_CURL_TOOL_UTIL_H */
