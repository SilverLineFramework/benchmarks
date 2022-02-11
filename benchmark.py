"""Send out benchmarks."""

import requests
import json
import uuid
import ssl
import paho.mqtt.client as mqtt


def get_runtimes(server="localhost:8000"):
    r = requests.get("http://{}/arts-api/v1/runtimes/".format(server))
    res = json.loads(r.text)

    return {rt['name']: rt['uuid'] for rt in res}


def create_message(filename, shortname, target):
    return json.dumps({
        "object_id": str(uuid.uuid4()),
        "action": "create",
        "type": "arts_req",
        "data": {
            "type": "module",
            "parent": {"uuid": target},
            "uuid": str(uuid.uuid4()),
            "name": shortname,
            "filename": filename,
            "filetype": "WA",
            "args": [filename],
            "env": []
        }
    })


polybench = [
    'pb_stencils_fdtd_2d', 'pb_medely_deriche', 'pb_la_blas_syr2k',
    'pb_la_solvers_gramschmidt', 'pb_la_blas_trmm', 'pb_la_kernels_atax',
    'pb_la_blas_symm', 'pb_la_kernels_bicg', 'pb_la_kernels_doitgen',
    'pb_la_kernels_2mm', 'pb_la_solvers_lu', 'pb_la_kernels_mvt',
    'pb_la_solvers_ludcmp', 'pb_stencils_adi', 'pb_medely_nussinov',
    'pb_medely_floyd_warshall', 'pb_stencils_seidel_2d',
    'pb_stencils_jacobi_2d', 'pb_la_solvers_cholesky', 'pb_la_kernels_3mm',
    'pb_stencils_heat_3d', 'pb_la_blas_syrk', 'pb_la_solvers_trisolv',
    'pb_la_blas_gemm', 'pb_stencils_jacobi_1d', 'pb_la_blas_gesummv',
    'pb_datamining_correlation', 'pb_datamining_covariance',
    'pb_la_blas_gemver', 'pb_la_solvers_durbin'
]
runtimes = get_runtimes()

print("Runtimes:")
print(runtimes)


with open("mqtt_pwd.txt") as f:
    mqtt_pwd = f.read()

client = mqtt.Client("benchmark_client")
client.username_pw_set("cli", mqtt_pwd)
client.tls_set(cert_reqs=ssl.CERT_NONE)
client.connect("localhost", 1883, 60)

for pb in polybench:
    print("Running: {}".format(pb))

    for k, v in runtimes.items():
        print("Running: {} [{}]".format(k, v))
        filename = "wasm-out/polybench/{}.wasm".format(pb)
        msg = create_message(filename, pb, v)
        print(msg)
        client.publish("realm/proc/control", msg)

    input()
