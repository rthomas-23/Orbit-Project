# Orbit-Project
first do this to download the pangolin graphics package (NB: for simplicity, do git clone in the downloads folder) <br />
pangolin library: https://github.com/stevenlovegrove/Pangolin/tree/master <br />
[in gitbash]... <br /> <br />
git clone https://github.com/Microsoft/vcpkg.git <br /> <br />
cd vcpkg <br /><br />
ls <br /><br />
./bootstrap-vcpkg.sh <br />   
./vcpkg.exe integrate install <br /><br />
./vcpkg.exe install pangolin <br /><br />

now cloning this repository... <br />
cloning steps: (if vcpkg is not in the same directory as where you want to put this project)... <br /><br />
git clone https://github.com/rthomas-23/Orbit-Project <br /><br />
cd Orbit-Project/ <br /><br />
mkdir build && cd build <br /><br />
cmake -DCMAKE_BUILD_TYPE=Release ..  <br /><br />
cmake --build . --config Release <br /><br />
(then open solution inside orbit-project/build) go from there <br /><br />
if cmake .. cannot find the Pangolin library. Try the following command: <br />
cmake -DCMAKE_BUILD_TYPE=Release ..  -DCMAKE_TOOLCHAIN_FILE=~/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake <br />
ensure " ~/Downloads/vcpkg/scripts/buildsystems/vcpkg.cmake " is the location of vcpkg <br />
