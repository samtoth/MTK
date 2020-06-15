import os

os.system("pipenv install --dev")
os.system("mkdir build")
os.chdir("build")
os.system("pipenv run conan config install ..")
os.system("pipenv run conan install -s build_type=Debug .. --build missing")
os.system("pipenv run conan build ..")
os.chdir("..")
