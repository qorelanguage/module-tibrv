AUTOMAKE_OPTIONS = foreign

SUBDIRS = src

noinst_HEADERS = src/QC_TibrvCmListener.h \
	src/QC_TibrvCmSender.h\
	src/QC_TibrvDistributedQueue.h \
	src/QC_TibrvFtMember.h \
	src/QC_TibrvFtMonitor.h \
	src/QC_TibrvListener.h \
	src/QC_TibrvSender.h \
	src/QoreTibrvCmListener.h \
	src/QoreTibrvCmSender.h \
	src/QoreTibrvCmTransport.h \
	src/QoreTibrvDistributedQueue.h \
	src/QoreTibrvFtMember.h \
	src/QoreTibrvFtMonitor.h \
	src/qore_tibrv.h \
	src/QoreTibrvListener.h \
	src/QoreTibrvSender.h \
	src/QoreTibrvTransport.h \
	src/tibrv-module.h

EXTRA_DIST = COPYING ChangeLog AUTHORS README \
	test/tibrv-test.q \
	docs/tibrv-module-doc.html \
        docs/qore-style.css \
        docs/img/acrobat_a.gif \
        docs/img/acrobat.gif \
        docs/img/disk.gif \
        docs/img/qbullet-note_a.gif \
        docs/img/qbullet-note.gif \
        docs/img/remote_a.gif \
        docs/img/remote.gif \
        docs/img/scrollup_a.gif \
        docs/img/scrollup.gif \
        docs/img/word.gif \
	qore-tibrv-module.spec

libtool: $(LIBTOOL_DEPS)
	$(SHELL) ./config.status --recheck
