/*
  modules/TIBCO/QoreTibrvSender.cc

  TIBCO Rendezvous integration to QORE

  Qore Programming Language

  Copyright 2003 - 2008 David Nichols

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <qore/Qore.h>

#include "QoreTibrvSender.h"

void QoreTibrvSender::sendSubject(const char *subject, const QoreHashNode *data, const char *replySubject, ExceptionSink *xsink)
{
   TibrvMsg msg;

   TibrvStatus status = msg.setSendSubject(subject);
   if (status != TIBRV_OK)
   {
      xsink->raiseException("TIBCO-INVALID-SUBJECT", "'%s': %s", subject, status.getText());
      return;
   }

   if (replySubject)
   {
      status = msg.setReplySubject(replySubject);
      if (status != TIBRV_OK)
      {
	 xsink->raiseException("TIBCO-INVALID-REPLY-SUBJECT", "'%s': %s", subject, status.getText());
	 return;
      }  
   }

   if (hashToMsg(&msg, data, xsink))
      return;

   //printd(5, "subject='%s' replySubject='%s'\n", subject, replySubject ? replySubject : "not set");
   send(&msg, xsink);
   //printd(0, "subject: %s msg=%08p sent OK\n", subject, data);
}

QoreHashNode *QoreTibrvSender::sendSubjectWithSyncReply(const char *subject, const QoreHashNode *data, int64 timeout, class ExceptionSink *xsink)
{
   TibrvMsg msg;

   TibrvStatus status = msg.setSendSubject(subject);
   if (status != TIBRV_OK)
   {
      xsink->raiseException("TIBCO-INVALID-SUBJECT", "'%s': %s", subject, status.getText());
      return NULL;
   }
   //printd(5, "subject: %s\n", subject);

   if (hashToMsg(&msg, data, xsink))
      return NULL;
   
   TibrvMsg reply;

   if (sendRequest(&msg, &reply, timeout, xsink))
      return NULL;

   return parseMsg(&reply, xsink);
}

