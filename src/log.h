/* $Id: log.h,v 1.2 2000-09-11 23:47:52 rjkaes Exp $
 *
 * See 'log.c' for a detailed description.
 *
 * Copyright (C) 1998  Steven Young
 * Copyright (C) 1999  Robert James Kaes (rjkaes@flarenet.com)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#ifndef _TINYPROXY_LOG_H_
#define _TINYPROXY_LOG_H_	

#ifdef HAVE_CONFIG_H
#  include "../config.h"
#endif

/*
 * Okay, I have modelled the levels for logging off the syslog() interface.
 * However, I would really prefer if only five of the levels are used. You
 * can see them below and I'll describe what each level should be for.
 * Hopefully tinyproxy will remain consistent with these levels.
 *	-- rjkaes
 *
 * Level	Description
 * -----	-----------
 * LOG_CRIT	This is catastrophic. Basically, tinyproxy can not recover
 *		from this and will either close the thread (if we're lucky),
 *		or the entire daemon. I would relegate this to conditions
 *		like unable to create the listening socket, or unable to
 *		create a thread. If you're going to log at this level provide
 *		as much information as possible.
 *
 * LOG_ERR	Okay, something bad happened. We can recover from this, but
 *		the connection will be terminated. This should be for things
 *		like when we cannot create a socket, or out of memory.
 *		Basically, the connection will not work, but it's not enough
 *		to bring the whole daemon down.
 *
 * LOG_WARNING	There is condition which will change the behaviour of
 *		tinyproxy from what is expected. For example, somebody did
 *		not specify a port. tinyproxy will handle this (by using
 *		it's default port), but it's a _higher_ level situation
 *		which the admin should be aware of.
 *
 * LOG_INFO	Everything else ends up here. Logging for incoming
 *		connections, denying due to filtering rules, unable to
 *		connect to remote server, etc.
 *
 * LOG_DEBUG	Don't use this level. :) Use the two DEBUG?() macros
 *		instead since they can remain in the source if needed. (I
 *		don't advocate this, but it could be useful at times.)
 */

#ifdef HAVE_SYSLOG_H
#  include <syslog.h>
#else
#  define LOG_CRIT    2
#  define LOG_ERR     3
#  define LOG_WARNING 4
#  define LOG_INFO    6
#  define LOG_DEBUG   7
#endif

/*
 * Use this for debugging. The format is specific:
 *    DEBUG1("There was a major problem");
 *    DEBUG2("There was a big problem: %s in connptr %p", "hello", connptr);
 */
#ifndef NDEBUG
# define DEBUG1(x)       log(LOG_DEBUG, "[%s:%d] " x, __FILE__, __LINE__)
# define DEBUG2(x, y...) log(LOG_DEBUG, "[%s:%d] " x, __FILE__, __LINE__, ## y)
#else
# define DEBUG1(x)       do { } while(0)
# define DEBUG2(x, y...) do { } while(0)
#endif

extern void log(short int level, char *fmt, ...);

#endif
