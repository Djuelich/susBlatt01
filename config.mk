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

