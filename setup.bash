export PROJECT_HOME_PATH=$(cd $(dirname "${BASH_SOURCE[0]}") && pwd -P)

function rebuild() {
    echo "******************* Cleaning Project... *********************"
    rm -rf $PROJECT_HOME_PATH/build
    mkdir $PROJECT_HOME_PATH/build
    cd $PROJECT_HOME_PATH/build
    cmake .. $@
    build
    cd $PROJECT_HOME_PATH
}

function build() {
    echo "******************* Building Project... *********************"
    cd $PROJECT_HOME_PATH/build
    cmake --build . -j$(($(nproc) / 2)) $@
    cd $PROJECT_HOME_PATH
}

function run_tests() {
    cd $PROJECT_HOME_PATH/build
    ctest --verbose
}

function repo_flashback() {
    echo "$1"
    mkdir Export
    local TO_EXPORT_LIST=()
    TO_EXPORT_LIST+=("$1")
    TO_EXPORT_LIST+=(".clang-format")
    TO_EXPORT_LIST+=("CMakeLists.txt")
    TO_EXPORT_LIST+=("NamingConvention.cpp")
    TO_EXPORT_LIST+=("ENV_SETUP.md")
    TO_EXPORT_LIST+=("README.md")
    TO_EXPORT_LIST+=("setup.bash")
    
    for TO_EXPORT in ${TO_EXPORT_LIST[*]}; do
        cp -r "${TO_EXPORT}" Export
    done
    
    # cd Export
    # sed '/^add_subdirectory/ d' < CMakeLists.txt > TmpCMakeLists.txt
    # rm CMakeLists.txt
    # mv TmpCMakeLists.txt CMakeLists.txt
    # echo "add_subdirectory($1)" |& tee -a CMakeLists.txt
    zip -r -q ../"$1".zip .
    cd ..
    rm -rf Export
}

function gen_pdf_docs() {
    pandoc -V geometry:margin=1in ENV_SETUP.md -o EnvironmentSetup.pdf
    pandoc -V geometry:margin=1in README.md -o ProgrammingLanguagesII.pdf
}