import os

env = Environment(CXXFLAGS="-std=c++0x")
env.Append(LIBS=['GL','glut','GLU','freeimage'])

common = SConscript('common/SConscript', exports = ['env'])

modelViewer = SConscript('modelViewer/SConscript', exports = ['env'])
sceneViewer = SConscript('sceneViewer/SConscript', exports = ['env'])
