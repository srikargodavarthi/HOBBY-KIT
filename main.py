import pyttsx3
import PyPDF2
book = open('pdc.pdf', 'rb')
pdfReader = PyPDF2.PdfFileReader(book)
pages = pdfReader.numPages

speaker = pyttsx3.init()
for num in range(4, pages):
    page = pdfReader.getPage(num)
    text = page.extractText()

    speaker.say(text)
    speaker.runAndWait()
