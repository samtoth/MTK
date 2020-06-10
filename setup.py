import os

os.system("pipenv install --dev")
os.system("pipenv run conan install . --build")
os.system("pipenv run conan build .")