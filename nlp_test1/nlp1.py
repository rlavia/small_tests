from textblob import TextBlob
from pprint import pprint

# We get started by importing spacy
import spacy
nlp = spacy.load("en_core_web_sm")


sentences = [
    'La comida estaba espectacular',
    #'The food we had yesterday at the restaurant was delicious, not expensive and quite healthy',
    #'My trip to London was very very long and enjoyable',
    #'I found the meal to be tasty and nice',
    #'The internet was slow.',
    #'Our experience was suboptimal'
]


for sentence in sentences:
    doc = nlp(sentence)
    # for token in doc:
    #  print(token.text, token.dep_, token.head.text, token.head.pos_, token.pos_,[child for child in token.children])


aspects = []
for sentence in sentences:
    doc = nlp(sentence)
    descriptive_term = ''
    target = ''
    for token in doc:
        if token.dep_ == 'nsubj' and token.pos_ == 'NOUN':
            target = token.text
        if token.pos_ == 'ADJ':
            prepend = ''
            for child in token.children:
                if child.pos_ != 'ADV':
                    continue
                prepend += child.text + ' '
            descriptive_term = prepend + token.text
            aspects.append({'text': doc.text, 'aspect': target, 'description': descriptive_term})
#print(aspects)


for aspect in aspects:
    print(TextBlob(aspect['text']).translate(from_lang="es", to="en",))
    aspect['sentiment'] = TextBlob(aspect['text']).translate(from_lang="es",to="en").sentiment
    #aspect['sentiment'] = TextBlob(aspect['text']).sentiment

#pprint(aspects)


for i in aspects:
    t = i["text"]
    s = i["sentiment"]
    p = s.polarity
    su = s.subjectivity
    print(f"text: {t} - sentiment: {s}")
