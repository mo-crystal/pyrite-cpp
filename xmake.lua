add_rules("mode.debug", "mode.release")

package("mocutils")
  set_urls("https://github.com/mo-crystal/mocutils.git")
  on_install("mingw", function (package)
    os.run("xmake f -p mingw")
    os.run("xmake")
    os.cp("src/*.h", package:installdir("include/mocutils"))
    os.cp("build/mingw/x86_64/release/*.a", package:installdir("lib"))
  end)
package_end()
add_requires("mocutils")

target("pyrite")
  set_kind("static")
  add_files("src/*.cc")
  add_packages("mocutils")

target("test")
  set_kind("binary")
  add_files("test/main.cc")
  add_packages("mocutils")

target("testpackage")
  set_kind("binary")
  add_files("test/package.cc")
  add_deps("pyrite")
  add_packages("mocutils")
