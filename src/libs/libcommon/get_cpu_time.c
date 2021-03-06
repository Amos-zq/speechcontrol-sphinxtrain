/* ====================================================================
 * Copyright (c) 1996-2000 Carnegie Mellon University.  All rights 
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * This work was supported in part by funding from the Defense Advanced 
 * Research Projects Agency and the National Science Foundation of the 
 * United States of America, and the CMU Sphinx Speech Consortium.
 *
 * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND 
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */
#include <sphinxbase/prim_type.h>
#include <s3/s3.h>

#if defined(__alpha)
#include <sys/time.h>
#include <sys/resource.h>
#endif

int
get_cpu_time(uint32 *sec, float32 *frac_sec)
{
#if defined(__alpha)
    int ret;
    struct rusage r_usage;
    uint32 out_sec;
    uint32 t_usec;
    uint32 out_usec;


    ret = getrusage(RUSAGE_SELF, &r_usage);
    if (ret < 0)
	return S3_ERROR;

    out_sec = 0;

    out_sec += r_usage.ru_utime.tv_sec;
    out_sec += r_usage.ru_stime.tv_sec;

    t_usec = r_usage.ru_utime.tv_usec+r_usage.ru_stime.tv_usec;

    out_sec += t_usec / 1000000;
    out_usec = t_usec % 1000000;

    *sec = out_sec;
    *frac_sec = (float32)out_usec / (float32)1000000;

    return S3_SUCCESS;
#else
    *sec = 0;
    *frac_sec = 0;

    return S3_SUCCESS;
#endif
}
