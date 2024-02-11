
import spacy

#nlp = spacy.load("es_core_news_sm")
#nlp = spacy.load("es_core_news_md")
#nlp = spacy.load("es_core_news_lg")
#nlp = spacy.load("es_dep_news_trf")

import es_core_news_lg

nlp = es_core_news_lg.load()
doc = nlp("La casa es azul.")
print([(w.text, w.pos_) for w in doc])
