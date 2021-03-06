SUBDIRS := $(wildcard ./[3-5]A)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); \
	do \
		$(MAKE) -C $$dir $@; \
	done

.PHONY: all $(SUBDIRS) clean
