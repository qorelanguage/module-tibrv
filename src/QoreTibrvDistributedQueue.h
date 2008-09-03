/*
  modules/TIBCO/QoreTibrvDistributedQueue.h

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

#ifndef _QORE_TIBCO_QORETIBRVDISTRIBUTEDQUEUE_H

#define _QORE_TIBCO_QORETIBRVDISTRIBUTEDQUEUE_H

#include <qore/Qore.h>

#include <tibrv/cmcpp.h>

#include "QoreTibrvTransport.h"

class QoreTibrvDistributedQueue : public AbstractPrivateData, public QoreTibrvTransport
{
   private:
      TibrvCmQueueTransport cmQueueTransport;
   
   protected:
      virtual ~QoreTibrvDistributedQueue() {}

   public:
      QoreTibrvDistributedQueue(const char *cmName, unsigned workerWeight, unsigned workerTasks, 
			        unsigned short schedulerWeight, int64 schedulerHeartbeat, int64 schedulerActivation,
				const char *desc, const char *service, const char *network, const char *daemon, class ExceptionSink *xsink);

      inline void setWorkerWeight(unsigned weight, class ExceptionSink *xsink)
      {
	 TibrvStatus status = cmQueueTransport.setWorkerWeight(weight);
	 if (status != TIBRV_OK)
	    xsink->raiseException("TIBRV-SETWORKERWEIGHT-ERROR", status.getText());
      }

      inline void setWorkerTasks(unsigned tasks, class ExceptionSink *xsink)
      {
	 TibrvStatus status = cmQueueTransport.setWorkerTasks(tasks);
	 if (status != TIBRV_OK)
	    xsink->raiseException("TIBRV-SETWORKERTASKS-ERROR", status.getText());
      }
      
      inline int64 getWorkerWeight(class ExceptionSink *xsink)
      {
	 unsigned weight;
	 TibrvStatus status = cmQueueTransport.getWorkerWeight(weight);
	 if (status != TIBRV_OK)
	    xsink->raiseException("TIBRV-GETWORKERWEIGHT-ERROR", status.getText());
	 return weight;
      }

      inline int64 getWorkerTasks(class ExceptionSink *xsink)
      {
	 unsigned tasks;
	 TibrvStatus status = cmQueueTransport.getWorkerTasks(tasks);
	 if (status != TIBRV_OK)
	    xsink->raiseException("TIBRV-GETWORKERTASKS-ERROR", status.getText());
	 return tasks;
      }
};

#endif
