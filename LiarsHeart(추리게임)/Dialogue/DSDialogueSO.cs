using System.Collections.Generic;
using UnityEngine;

public class DSDialogueSO : ScriptableObject
{
    [field: SerializeField] public string DialogueName { get; set; }
    [field: SerializeField] [field: TextArea()] public string Text { get; set; }
    [field: SerializeField] public Sprite Background { get; set; }
    [field: SerializeField] public AudioClip BGM { get; set; }
    [field: SerializeField] public List<DSDialogueSpeakerData> Speaker { get; set; }
    [field: SerializeField] public SerializableDictionary<int, AudioClip> SoundEffects { get; set; }
    [field: SerializeField] public List<DSDialogueChoiceData> Choices { get; set; }
    [field: SerializeField] public DSDialogueType DialogueType { get; set; }
    [field: SerializeField] public bool IsStartingDialogue { get; set; }

    public void Initialize(string dialogueName, string text, Sprite background, AudioClip bgm, List<DSDialogueSpeakerData> speaker, List<DSDialogueSoundData> soundEffects, List<DSDialogueChoiceData> choices, DSDialogueType dialogueType, bool isStartingDialogue)
    {
        DialogueName = dialogueName;
        Text = text;
        Background = background;
        BGM = bgm;
        Speaker = speaker;
        Choices = choices;
        DialogueType = dialogueType;
        IsStartingDialogue = isStartingDialogue;

        foreach(DSDialogueSoundData soundEffect in soundEffects)
        {
            if(!SoundEffects.ContainsKey(soundEffect.Index))
            {
                SoundEffects.Add(soundEffect.Index, soundEffect.AudioClip);
            }
        }
    }
}
