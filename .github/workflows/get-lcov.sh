mkdir Iconv
cd Iconv
curl https://github.com/linux-test-project/lcov/archive/refs/tags/v1.16.zip -L -o src.zip
unzip src.zip
cd lcov-1.16
sudo make install
