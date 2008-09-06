
SOURCES=bookinfo.docbook tibrv-module.docbook

all: tibrv-module-doc.html

tibrv-module-doc.html: $(SOURCES)
	#docbook2html -u module.docbook
	xsltproc -o $@ driver.xsl module.docbook

