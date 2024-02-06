import os
import IPython
import matplotlib
import matplotlib.pyplot as plt
import requests
import torch
import torchaudio

print("")

SPEECH_URL = "https://keithito.com/LJ-Speech-Dataset/LJ025-0076.wav"
#SPEECH_FILE = "_assets/speech.wav"
#SPEECH_FILE = "_assets/OSR_us_000_0010_8k.wav"
#SPEECH_FILE = "_assets/WhatsApp Ptt 2023-10-02 at 19.50.58.ogg"
#SPEECH_FILE = "_assets/WhatsApp Ptt 2023-10-02 at 22.25.44.ogg"

SPEECH_FILE = "_assets/WhatsApp Ptt 2023-10-02 at 23.25.32.ogg"




if not os.path.exists(SPEECH_FILE):
    os.makedirs("_assets", exist_ok=True)
    with open(SPEECH_FILE, "wb") as file:
        file.write(requests.get(SPEECH_URL).content)



device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
print(f"Using device {device}")
bundle = torchaudio.pipelines.WAV2VEC2_ASR_BASE_960H
print(f"Sample Rate: {bundle.sample_rate}")
print(f"Labels: {bundle.get_labels()}")
model = bundle.get_model().to(device)
#print(model.__class__)


waveform, sample_rate = torchaudio.load(SPEECH_FILE)
waveform = waveform.to(device)
if sample_rate != bundle.sample_rate:
    waveform = torchaudio.functional.resample(waveform, sample_rate, bundle.sample_rate)


with torch.inference_mode():
    emission, _ = model(waveform)

plt.imshow(emission[0].cpu().T)
plt.title("Classification result")
plt.xlabel("Frame (time-axis)")
plt.ylabel("Class")
#plt.show()
#print("Class labels:", bundle.get_labels())

class GreedyCTCDecoder(torch.nn.Module):
    def __init__(self, labels, blank=0):
        super().__init__()
        self.labels = labels
        self.blank = blank

    def forward(self, emission: torch.Tensor) -> str:
        """Given a sequence emission over labels, get the best path string
        Args:
        emission (Tensor): Logit tensors. Shape `[num_seq, num_label]`.
        Returns:
        str: The resulting transcript
        """
        indices = torch.argmax(emission, dim=-1) # [num_seq,]
        indices = torch.unique_consecutive(indices, dim=-1)
        indices = [i for i in indices if i != self.blank]
        return "".join([self.labels[i] for i in indices])
    




decoder = GreedyCTCDecoder(labels=bundle.get_labels())
transcript = decoder(emission[0])


print("")
print("")
print(transcript)
print("")
print("")