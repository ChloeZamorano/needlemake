# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug_windows
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug_windows)
  mini_yaml_config = debug_windows
  needlemake_config = debug_windows

else ifeq ($(config),release_windows)
  mini_yaml_config = release_windows
  needlemake_config = release_windows

else ifeq ($(config),deploy_windows)
  mini_yaml_config = deploy_windows
  needlemake_config = deploy_windows

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := mini-yaml needlemake

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

mini-yaml:
ifneq (,$(mini_yaml_config))
	@echo "==== Building mini-yaml ($(mini_yaml_config)) ===="
	@${MAKE} --no-print-directory -C . -f mini-yaml.make config=$(mini_yaml_config)
endif

needlemake: mini-yaml
ifneq (,$(needlemake_config))
	@echo "==== Building needlemake ($(needlemake_config)) ===="
	@${MAKE} --no-print-directory -C . -f needlemake.make config=$(needlemake_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f mini-yaml.make clean
	@${MAKE} --no-print-directory -C . -f needlemake.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug_windows"
	@echo "  release_windows"
	@echo "  deploy_windows"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   mini-yaml"
	@echo "   needlemake"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"