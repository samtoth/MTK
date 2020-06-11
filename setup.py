import os

os.system("pipenv install")
os.system("pipenv run conan install . --build")
os.system("pipenv run conan build .")