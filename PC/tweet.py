
import webbrowser
from urllib.parse import quote

text = "ゆれた"


def tweet():
    webbrowser.open(f"https://twitter.com/intent/tweet?text={quote(text)}")


if __name__ == '__main__':
    tweet()
