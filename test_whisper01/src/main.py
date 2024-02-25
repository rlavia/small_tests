import whisper

model = whisper.load_model("base")
#model = whisper.load_model("small")
#model = whisper.load_model("medium")

print("\n\n")

result = model.transcribe("./assets/ya_lo_vas_a_entender.wav")
print(result["text"])
print("\n\n")

result = model.transcribe("./assets/debate_beagle.wav")
print(result["text"])
print("\n\n")

result = model.transcribe("./assets/larreta_milei.wav")
print(result["text"])
print("\n\n")

result = model.transcribe("./assets/gekko.wav")
print(result["text"])
print("\n\n")

exit(0)


