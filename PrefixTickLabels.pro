TEMPLATE = subdirs

SUBDIRS += demo
SUBDIRS += src
SUBDIRS += tests

demo.depends += src
tests.depends += src
