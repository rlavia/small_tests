
from sentiment_analysis_spanish import sentiment_analysis

sentiment = sentiment_analysis.SentimentAnalysisSpanish()

#print(round(sentiment.sentiment("me gusta la tombola es genial"),2))
#print(round(sentiment.sentiment("me parece terrible esto que me estás diciendo"),2))
print(round(sentiment.sentiment("Esa película me gustó mucho"),2))
print(round(sentiment.sentiment("Esa película me encantó"),2))
print(round(sentiment.sentiment("Esa película me gustó un poco"),2))
print(round(sentiment.sentiment("Esa película no me encantó"),2))
print(round(sentiment.sentiment("Esa película no me gustó"),2))
print(round(sentiment.sentiment("Esa película fue una reverenda porquería"),2))
