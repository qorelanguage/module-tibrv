if COND_SINGLE_COMPILATION_UNIT
TIBRV_SOURCES = single-compilation-unit.cc
else
TIBRV_SOURCES = tibrv.cc \
	QoreTibrvTransport.cc \
	QoreTibrvSender.cc \
	QoreTibrvListener.cc \
	QoreTibrvFtMember.cc \
	QoreTibrvFtMonitor.cc \
	QoreTibrvCmTransport.cc \
	QoreTibrvCmSender.cc \
	QoreTibrvCmListener.cc \
	QoreTibrvDistributedQueue.cc \
	QC_TibrvSender.cc \
	QC_TibrvListener.cc \
	QC_TibrvFtMember.cc \
	QC_TibrvFtMonitor.cc \
	QC_TibrvCmSender.cc \
	QC_TibrvCmListener.cc \
	QC_TibrvDistributedQueue.cc \
	tibrv-module.cc
endif

lib_LTLIBRARIES = tibrv.la
tibrv_la_SOURCES = $(TIBRV_SOURCES)
tibrv_la_LDFLAGS = -module -avoid-version $(TIBRV_LDFLAGS) $(TIBRVCPP_LDFLAGS)
tibrv_la_CPPFLAGS = $(TIBRV_CPPFLAGS)

INCLUDES = -I$(top_srcdir)/include

if COND_PROFILE
AM_CXXFLAGS=-g -pg
else
if COND_DEBUG
AM_CXXFLAGS=-g
endif
endif

install-exec-hook:
	mv $(libdir)/tibrv.$(MODULE_SUFFIX) $(libdir)/tibrv.qmod
	rm -f $(libdir)/tibrv.la
