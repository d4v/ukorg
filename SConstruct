Help("""
Type: 'scons' to build silently,
      'scons -jN' with N jobs
      'scons VERBOSE=1' to view compil commands
    """)

env = DefaultEnvironment()

#for item in sorted(env.Dictionary().items()):
#      print "construction variable = '%s', value = '%s'" % item

if ARGUMENTS.get('VERBOSE') != '1':
  env['CXXCOMSTR']    = "Compiling $TARGET"
  env['CCCOMSTR']     = "Compiling $TARGET"
  env['SHCXXCOMSTR']  = "Compiling $TARGET"
  env['SHCCCOMSTR']   = "Compiling $TARGET"
  env['LINKCOMSTR']   = "Linking   $TARGET"
  env['RANLIBCOMSTR'] = "Indexing  $TARGET"
  env['ARCOMSTR']     = "Building  $TARGET"
  env['SHLINKCOMSTR'] = "Building  $TARGET"

env.PrependUnique(CCFLAGS=['-g','-Wall','-Werror'])

Export('env')

SConscript('lib/SConscript', variant_dir='build/lib', duplicate=0)
SConscript('ui/SConscript' , variant_dir='build/ui' , duplicate=0)

