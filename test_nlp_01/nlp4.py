from argostranslate import package, translate
from textblob import TextBlob

import spacy
nlp = spacy.load("en_core_web_lg")

package.install_from_path('translate-es_en-1_0.argosmodel')

sentences = [
    'comida',
    'amor',
    'lindo',
    'feo',
    'feliz',
    'triste',
    'like',
    'liked',
    'La comida estaba espectacular.',
    'La comida era mala.',
    'Ese producto era muy bueno',
    'Ese producto era muy malo',
    'Me gustó mucho el contenido',
    'No me gustó el contenido',
    'No es lo que esperaba',
    'No me gustó nada',
    'Esto está lleno de sentimientos negativos',
    'Solo siento tristeza y angustia',
    'Estoy repleto de felicidad y alegria',
    'Triste',
    'Me quiero morir ahora mismo',
    'Es la película más horrible que he visto en toda mi vida',
    'La película es horrible'
]


def translate_sp_to_en(s):
    installed_languages = translate.get_installed_languages()
    translation_en_es = installed_languages[1].get_translation(installed_languages[0])
    return translation_en_es.translate(s)

for i in sentences:
    print(i)
    en = translate_sp_to_en(i)
    en = en.replace('.','')
    print(en)
    doc = nlp(en)
    descriptive_term = ''
    target = ''
    for token in doc:
        print(str(token) + " " + token.pos_ + " " + token.dep_)
        if token.dep_ == 'nsubj': #and token.pos_ == 'NOUN':
            target = token.text
        if token.pos_ == 'ADJ':
            prepend = ''
            for child in token.children:
                if child.pos_ not in ['ADV', 'acomp']:
                    continue
                prepend += child.text + ' '
            descriptive_term = prepend + token.text
            print({ 'aspect': target, 'description': descriptive_term})

    sent = TextBlob(en).sentiment
    print(sent)
    print("")