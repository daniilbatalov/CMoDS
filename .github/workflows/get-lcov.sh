mkdir Iconv
pushd Iconv
curl https://github.com/linux-test-project/lcov/archive/refs/tags/v1.16.zip -L -o src.zip
unzip src.zip
pushd lcov-1.16
sudo make install
popd
popd
