WASM_APPS="${PWD}/wasm-apps"
WAMR_DIR="${PWD}/../wasm-micro-runtime"
OUT_DIR="${PWD}/wasm-out"
WAMR_SYMBOLS="wamr-sdk/app/libc-builtin-sysroot/share/defined-symbols.txt"

mkdir "${OUT_DIR}"

cd "${WASM_APPS}"
for i in `ls *.c`
do
APP_SRC="$i"
OUT_FILE=${i%.*}.wasm

/opt/wasi-sdk/bin/clang \
        -O0 -z stack-size=4096 -Wl,--initial-memory=65536 \
        -Wl,--allow-undefined-file="${WAMR_DIR}/${WAMR_SYMBOLS}" \
        -Wl,--no-threads,--strip-all,--no-entry\
        -Wl,--export=main\
        -Wl,--export=_start\
        -Wl,--allow-undefined \
        -o "${OUT_DIR}/${OUT_FILE}" "${APP_SRC}"

if [ -f "${OUT_DIR}/${OUT_FILE}" ]; then
        echo "build ${OUT_FILE} success"
else
        echo "build ${OUT_FILE} fail"
fi
done
