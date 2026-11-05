include ../../include/xpp/flags.makefile

# CXX=clang
CXXFLAGS+=-g
# CXXFLAGS+=-Wextra
# CXXFLAGS+=-ftime-report

CPPSRCS=event.cpp \
        requests.cpp \
        iterator.cpp

all: ${CPPSRCS}

${CPPSRCS}:
	${CXX} ${CXXFLAGS} -o $(@:%.cpp=%) $@ ${LDLIBS}

xlib-test: xlib-test.cpp
	${CXX} $(shell pkg-config --libs --cflags x11 xrandr) -o $@ $<

version:

clean:
	rm -f ${CPPSRCS:%.cpp=%}

.PHONY: ${CPPSRCS} clean
