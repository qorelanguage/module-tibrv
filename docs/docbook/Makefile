
SOURCES=bookinfo.docbook tibrv-module.docbook

DOCBOOK_ROOT := $(shell ./get-docbook-root.sh)

all: tibrv-module-doc.html

tibrv-module-doc.html: $(SOURCES)
	#docbook2html -u module.docbook
	xsltproc --stringparam html.stylesheet qore-style.css \
                 --stringparam use.id.as.filename 1 \
                 --stringparam generate.toc "book toc,title" \
                 --stringparam toc.max.depth 2 \
		 --output $@ \
		 ${DOCBOOK_ROOT}/docbook.xsl \
		 module.docbook

