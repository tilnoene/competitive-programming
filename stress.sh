# change the file names in main function, where:
# generator = code to generate an input
# solution = your main solution
# brute = a bad (but work) solution

MAX_TESTS="100"

function compile() {
    local file="$1"
    local exe_name="$2"

    g++ -std=c++17 "${file}" -o "${exe_name}" || { echo "Error when compiling: ${file}"; exit 1; }

    echo "Compiled ${file}."
}

function stress_test() {
    for ((i=0; i<$MAX_TESTS; i++)); do
        ./generator > input.in
        ./solution < input.in > solution.out
        ./brute < input.in > brute.out

        if diff -F --label --side-by-side --ignore-space-change solution.out brute.out > /dev/null; then
            echo "test #$i: ok"
        else
            echo "test #$i: failed"
            break
        fi
    done
}

function main() {
    compile "generator.cpp" "generator"
    compile "solution.cpp" "solution"
    compile "brute.cpp" "brute"
    stress_test
}

main "$@"