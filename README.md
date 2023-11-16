# Orbit-Project
first do this
NB: do git clone in the downloads folder <br />
git clone https://github.com/Microsoft/vcpkg.git
   
cd vcpkg/

ls
   
./bootstrap-vcpkg.sh
   
./vcpkg.exe integrate install
   
./vcpkg.exe install pangolin

Commands to run from GitBash

We used the library of Pangolin https://github.com/stevenlovegrove/Pangolin/tree/master


cloning steps: (if vcpkg is not in the same directory as where you want to put this project) <br /><br />
git clone https://github.com/rthomas-23/Orbit-Project <br />

cd Orbit-Project/ <br />
 
mkdir build && cd build <br />

cmake -DCMAKE_BUILD_TYPE=Release ..  <br />

cmake --build . --config Release <br />

(then open solution inside orbit-project/build) go from there <br />

if cmake .. cannot find the Pangolin library. Try the following command: <br />
cmake -DCMAKE_BUILD_TYPE=Release ..  -DCMAKE_TOOLCHAIN_FILE=~/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake <br />
ensure ~/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake is the location of vcpkg <br />
