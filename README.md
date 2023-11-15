# Orbit-Project
first do this

   21  git clone https://github.com/Microsoft/vcpkg.git
   
   22  cd vcpkg/
   
   23  ls
   
   24  ./bootstrap-vcpkg.sh
   
   25  ./vcpkg.exe integrate install
   
   26  ./vcpkg.exe install pangolin

  Commands to run from GitBash

  We used the library of Pangolin https://github.com/stevenlovegrove/Pangolin/tree/master


cloning steps:
git clone https://github.com/rthomas-23/Orbit-Project <br />

cd Orbit-Project/ <br />
 
mkdir build && cd build <br />

cmake -DCMAKE_BUILD_TYPE=Release .. -DCMAKE_TOOLCHAIN_FILE=~/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake <br />

cmake --build . --config Release <br />

(then open solution inside orbit-project/build) go tfromthere

if cmake .. cannot find the Pangolin library. Try the following command:
