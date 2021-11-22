
from os.path import expanduser
import os
from glob import glob
import subprocess

home = expanduser("~")


repo_paths = [
    f"{home}\IoTGit\*"
]


def commit_push():
    for path in repo_paths:
        for dir in (glob(path)):
            print(f"go to {dir}")
            os.chdir(dir)
            try:
                print("COMMIT")
                subprocess.run(
                    ["git", "commit", "-a", "-m", "[skip ci] WIP: commit due to emergency"])

            except:
                pass

            branch = subprocess.run(
                ["git", "symbolic-ref", "--short", "HEAD"], encoding='utf-8', stdout=subprocess.PIPE).stdout.rstrip("\n")

            print(f"branch is {branch}")

            hash = subprocess.run(
                ["git", "rev-parse",  "HEAD"], encoding='utf-8', stdout=subprocess.PIPE).stdout.rstrip("\n")

            print(f"hash is ${hash}")

            print("PUSH")

            subprocess.run(
                ["git", "push", "origin", f"{branch}:wip-{branch}-{hash}"])


if __name__ == '__main__':
    commit_push()
