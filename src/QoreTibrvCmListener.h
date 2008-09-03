/*
  modules/TIBCO/QoreTibrvCmListener.h

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

#ifndef _QORE_TIBCO_QORETIBRVCMLISTENER_H

#define _QORE_TIBCO_QORETIBRVCMLISTENER_H

#include <qore/Qore.h>

#include "QoreTibrvCmTransport.h"

class QoreTibrvCmListener : public AbstractPrivateData, public QoreTibrvCmTransport
{
   private:
      TibrvCmListener cmListener;
      TibrvQueue queue;
      class QoreTibrvCmMsgCallback *callback;

   protected:
      virtual ~QoreTibrvCmListener();

   public:
      QoreTibrvCmListener(const char *subject, const char *cmName, bool requestOld, const char *ledgerName, bool syncLedger, const char *relayAgent, 
			  const char *desc, const char *service, const char *network, const char *daemon, class ExceptionSink *xsink);

      inline int getQueueSize(class ExceptionSink *xsink)
      {
	 tibrv_u32 count;
	 TibrvStatus status = queue.getCount(count);
	 if (status != TIBRV_OK)
	 {
	    xsink->raiseException("TIBRVCMLISTENER-GETQUEUESIZE-ERROR", status.getText());
	    return 0;
	 }
	 
	 return count;
      }

      QoreHashNode *getMessage(class ExceptionSink *xsink);
      QoreHashNode *getMessage(int64 timeout, class ExceptionSink *xsink);

      QoreStringNode *createInboxName(class ExceptionSink *xsink)
      {
	 char name[120];
	 
	 TibrvStatus status = transport.createInbox(name, 119);
	 if (status != TIBRV_OK)
	 {
	    xsink->raiseException("TIBRVCMLISTENER-CREATEINBOXNAME-ERROR", "cannot create inbox name: %s", status.getText());
	    return NULL;
	 }
	 return new QoreStringNode(name);
      }
};

// each dispatched event calling onMsg() must be followed by a getMessage() call
class QoreTibrvCmMsgCallback : public TibrvCmMsgCallback
{
   private:
      QoreTibrvCmListener *ql;
      ExceptionSink xsink;
      QoreHashNode *h;
      
      virtual void onCmMsg(TibrvCmListener *cmListener, TibrvMsg &msg)
      {
	 h = ql->parseMsg(&msg, &xsink);
	 // add certified information if available
	 if (h)
	 {
	    const char *name;
	    if (TibrvCmMsg::getSender(msg, name) == TIBRV_OK)
	       h->setKeyValue("cmSender", new QoreStringNode(name), NULL);
	    
	    tibrv_u64 seq;
	    if (TibrvCmMsg::getSequence(msg, seq) == TIBRV_OK)
	       h->setKeyValue("cmSequence", new QoreBigIntNode((int64)seq), NULL);
	 }
      }

   public:
      inline QoreTibrvCmMsgCallback(class QoreTibrvCmListener *l)
      {
	 ql = l;
	 h = NULL;
      }

      virtual ~QoreTibrvCmMsgCallback()
      {
	 if (h)
	    h->deref(&xsink);
      }

      inline QoreHashNode *getMessage(class ExceptionSink *xs)
      {
	 if (xsink.isException())
	 {
	    xs->assimilate(&xsink);
	    return NULL;
	 }
	 QoreHashNode *rv = h;
	 h = NULL;
	 return rv;
      }
};

inline QoreTibrvCmListener::~QoreTibrvCmListener() 
{ 
   if (callback)
      delete callback; 
}

#endif
