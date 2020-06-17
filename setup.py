import os
import sys
import argparse

verbose = False


def run(cmd: str, fatal: bool = True):
    if verbose:
        print(f" -- RUN\t\"{cmd}\"")
    code = os.system(cmd)
    if code != 0:
        if fatal:
            sys.exit(code)
        else:
            print(f" -- Warning command exited with code {code}")
    return code


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Run MTK first time setup.')
    parser.add_argument("--generator", help="specify cmake generator")
    parser.add_argument("--verbose", help="Verbose console output", action="store_true")

    args = parser.parse_args()
    verbose = args.verbose

    run("pipenv install --dev")
    run("mkdir build", fatal=False)
    os.chdir("build")
    run("pipenv run conan config install ..")
    if args.generator is not None:
        run(f"pipenv run conan install -s build_type=Debug -o generator=\"{args.generator}\" .. --build missing")
    else:
        run("pipenv run conan install -s build_type=Debug .. --build missing")
    ret = run("pipenv run conan build ..")
    os.chdir("..")

    sys.exit(ret)
