SUBDIRS := $(wildcard ./TP*)

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	for dir in $(SUBDIRS); \
	do \
		$(MAKE) -C $$dir $@; \
	done

.PHONY: all $(SUBDIRS) clean