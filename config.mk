# Regeln fuer die bedingte Uebersetzung von vollstaendigen Dateien
# ----------------------------------------------------------------
#
# Variablen:
# SRC := Alle Uebersetzungseinheiten, sprich C/C++-Dateien (*.c und *.cc)
# ASPECTSRC := Alle Aspekt-Dateien (*.ah)
#
# Die Namen aller KConfig-Merkmale sind hier mit dem Prefix CONFIG_ versehen.
#

# Konfiguration von zwei Aspekten zur Debugging-Unterstuetzung
ifneq ($(CONFIG_DEBUG_PANIC),y)
  ASPECTSRC := $(filter-out %/show_panic.ah,$(ASPECTSRC))
endif
ifneq ($(CONFIG_DEBUG_GUARD),y)
  ASPECTSRC := $(filter-out %/locker_checking.ah,$(ASPECTSRC))
endif

ifneq ($(CONFIG_WECKER), y)
	SRC := $(filter-out %/wecker.cc, $(SRC))
	ASPECTSRC := $(filter-out %/wecker.ah,$(ASPECTSRC))
endif

ifneq ($(CONFIG_CPU_WATCH), y)
	SRC := $(filter-out %/cpuwatch.cc, $(SRC))
	ASPECTSRC := $(filter-out %/idletimer.ah,$(ASPECTSRC))
endif

ifneq ($(CONFIG_FUNK), y)
	SRC := $(filter-out %/funk.cc, $(SRC))
	ASPECTSRC := $(filter-out %/funk.ah,$(ASPECTSRC))
endif

ifneq ($(CONFIG_BUTTON_SERVICE), y)
	SRC := $(filter-out %/buttonservice.cc, $(SRC))
	ASPECTSRC := $(filter-out %/buttonservice.ah,$(ASPECTSRC))
endif

ifneq ($(CONFIG_BIZEPS), y)
	SRC := $(filter-out %/bizeps.cc, $(SRC))
	ASPECTSRC := $(filter-out %/bizeps.ah,$(ASPECTSRC))
endif
