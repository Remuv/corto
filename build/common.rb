
CWD = Dir.pwd

def msg(text)
  print "[ #{C_DEFAULT}#{text}#{C_NORMAL} ]\n"
end

def cmd(command)
  sh command
end

# Set Corto version variable
if ENV['CORTO_VERSION'] then
  CORTO_VERSION = ENV['CORTO_VERSION']
else
  CORTO_VERSION = `corto --minor`.strip
end

# Set platform variables
CORTO_OS = `uname -s`.strip if
CORTO_MACHINE = `uname -m`.strip
CORTO_PLATFORM = CORTO_OS + "-" + CORTO_MACHINE

# Set verbosity
if not defined? VERBOSE then
  if ENV['verbose'] == "true" then
    VERBOSE = true
    ENV['CORTO_VERBOSITY'] = "TRACE"
  elsif not ENV['CORTO_VERBOSITY'] or ENV['CORTO_VERBOSITY'] == "" or ENV['CORTO_VERBOSITY'] == "OK" then
    VERBOSE = false
  else
    VERBOSE = true
  end
end

# Enable debugging of buildsystem (use valgrind on corto commands)
if not defined? DEBUGCMD then
  if ENV['debug'] == "true" then
    DEBUGCMD = "valgrind --track-origins=yes --num-callers=50 "
  else
    DEBUGCMD = ""
  end
end

# Set coverage
if not defined? COVERAGE then
  if ENV['coverage'] == "true" then
    COVERAGE = true
  else
    COVERAGE = false
  end
end

# Set softlinks
if not defined? SOFTLINKS then
  if ENV['softlinks'] == "false" then
    SOFTLINKS = false
  else
    SOFTLINKS = true
  end
end

# Set multithreading
if not defined? MULTITHREAD then
  if ENV['multithread'] == "false" then
    MULTITHREAD = false
  else
    MULTITHREAD = true
  end
end

# Set dryrun
if not defined? DRYRUN then
  if ENV['dryrun'] == "true" then
    DRYRUN = true
  else
    DRYRUN = false
  end
end

# Set config
if not defined? CONFIG then
  if not ENV['config'] or ENV['config'] == "" then
    CONFIG = "debug"
  else
    CONFIG = ENV['config']
  end
end

# Set colors
C_DEFAULT = "\033[1;36m"
C_BOLD = "\033[0;49m\033[1;49m"
C_NORMAL = "\033[0;49m"
C_FAIL = "\033[1;31m"
C_OK = "\033[1;32m"
C_WARNING = "\033[1;33m"

# Initialize public variables
INCLUDE = [] if not defined? INCLUDE
LIB = [] if not defined? LIB
LIBPATH = [] if not defined? LIBPATH
LINK = [] if not defined? LINK
CFLAGS = ["-pedantic", "-Wstrict-prototypes"] if not defined? CFLAGS
CXXFLAGS = [] if not defined? CXXFLAGS
LFLAGS = [] if not defined? LFLAGS
LOCAL = false if not defined? LOCAL
USE_PACKAGE = [] if not defined? USE_PACKAGE
DEFINE = [] if not defined? DEFINE
PP_PRELOAD = [] if not defined? PP_PRELOAD
LANGUAGE = "c" if not defined? LANGUAGE
ALWAYS_REBUILD = [] if not defined? ALWAYS_REBUILD
UNINSTALL = []

# Variable that tracks files created by the buildsystem for uninstaller

# Set environment variables in local constants
CORTO_TARGET = ENV['CORTO_TARGET']
CORTO_BUILD = ENV['CORTO_BUILD']
CORTO_HOME = ENV['CORTO_HOME']

# Set compiler
if not defined? CC then
  CC = if ENV['CC'].nil? or ENV['CC'].empty?
    "cc"
  else
    ENV['CC']
  end
end
if not defined? CXX then
  CXX = if ENV['CXX'].nil? or ENV['CXX'].empty?
    "g++"
  else
    ENV['CXX']
  end
end

# Set default extension
EXT = if LANGUAGE == "c" then
  "c"
else
  "cpp"
end

# Set root path
CORTO_BUILDROOT = if ENV['CORTO_BUILDROOT'].nil? or ENV['CORTO_BUILDROOT'].empty?

  # First time rake is called
  if ENV['silent'] != "true" then
    if ENV['show_header'] != "false" then
      print "#{C_BOLD}corto buildsystem v#{CORTO_VERSION}#{C_NORMAL}\n"
      print "\n"
    end
    if ENV['binaries'] != "false" then
      print "  Corto apps & packages are installed to #{C_DEFAULT}#{CORTO_TARGET}#{C_NORMAL}.\n"
      if ENV['redis'] != "false" then
        print "  The #{C_DEFAULT}#{CORTO_TARGET}/redis/corto/#{CORTO_VERSION}#{C_NORMAL} directory contains\n"
        print "  binaries that can be embedded in other (non-corto) projects.\n"
      end
      print "\n"
    end

    tool = `which corto`
    if $?.exitstatus == 0 then
      print "  #{`corto --version`}"
      print "  tool:    #{tool}\n"
    end
    msg "start from #{C_BOLD}#{Dir.pwd}"
    msg "config #{C_BOLD}#{CONFIG}"
  end

  ENV['CORTO_BUILDROOT'] = Dir.pwd
  Dir.pwd
else
  ENV['CORTO_BUILDROOT']
end

include_ld_path =  "#{ENV['CORTO_TARGET']}/lib"
include_ld_path += ":#{ENV['CORTO_TARGET']}/redis/corto/#{CORTO_VERSION}/lib"
include_ld_path += ":/usr/local/redis/corto/#{CORTO_VERSION}/lib"
ENV["LD_LIBRARY_PATH"] = "#{include_ld_path}:#{ENV["LD_LIBRARY_PATH"]}"

# Utility that replaces buildsystem tokens with actual values
def corto_replace(str)
    str = str.gsub("$(CORTO_OS)", CORTO_OS)
    str = str.gsub("$(CORTO_MACHINE)", CORTO_MACHINE)
    str = str.gsub("$(CORTO_PLATFORM)", CORTO_PLATFORM)
    str = str.gsub("$(CORTO_TARGET)", TARGETDIR)
    str = str.gsub("$(CORTO_VERSION)", CORTO_VERSION)
    projectPath = ""
    if defined? PACKAGEDIR then
        projectPath = PACKAGEDIR
    end
    str = str.gsub("$(CORTO_ETC)", ENV['CORTO_TARGET'] + "/etc/corto/#{CORTO_VERSION}/" + projectPath)
    str = str.gsub("$(CORTO_INCLUDE)", ENV['CORTO_TARGET'] + "/include/corto/#{CORTO_VERSION}/" + projectPath)
    str = str.gsub("$(CORTO_LIB)", ENV['CORTO_TARGET'] + "/lib/corto/#{CORTO_VERSION}/" + projectPath)
end

def corto_section(package, section)
    s = ENV["CORTO_TARGET"] + "/#{section}/corto/#{CORTO_VERSION}/#{package}"
    corto_replace(s)
end
