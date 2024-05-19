using UnityEngine;
using DS.ScriptableObjects;
using System.Collections.Generic;

public class DialogueManager
{
    [SerializeField] private int maxLife = 5;
    public int MaxLife { get => maxLife; }

    [SerializeField] private int curLife;
    public int CurLife { get => curLife; }

    private List<DSDialogueSO> savedDialogueData = new List<DSDialogueSO>();
    public List<DSDialogueSO> SavedDialogueData { get => savedDialogueData; }

    // BroadCasting
    [SerializeField] private DialogueEventChannelSO setDialogueEvent;
    [SerializeField] private DialogueEventChannelSO selectDialogueEvent;

    [SerializeField] private VoidEventChannelSO endDialogueEvent;
    [SerializeField] private VoidEventChannelSO createLifeEvent;
    [SerializeField] private VoidEventChannelSO inCorrectSelectEvent;

    const string path = "Events/Dialogue/";

    public void Init()
    {
        curLife = maxLife;

        setDialogueEvent = Resources.Load<DialogueEventChannelSO>(path + "SetDialogueEvent");
        selectDialogueEvent = Resources.Load<DialogueEventChannelSO>(path + "SelectDialogueEvent");
        endDialogueEvent = Resources.Load<VoidEventChannelSO>(path + "EndDialogueEvent");
        createLifeEvent = Resources.Load<VoidEventChannelSO>(path + "CreateLifeEvent");
        inCorrectSelectEvent = Resources.Load<VoidEventChannelSO>(path + "InCorrectSelectEvent");
    }

    public void PlayDialogue(DSDialogueSO dialogue)
    {
        if (dialogue == null)
        {
            curLife = maxLife;
            endDialogueEvent.RaiseEvent();
            savedDialogueData.Clear();
            return;
        }

        if (dialogue.Choices == null)
        {
            curLife = maxLife;
            endDialogueEvent.RaiseEvent();
            savedDialogueData.Clear();
            return;
        }

        savedDialogueData.Add(dialogue);

        SetBGM(dialogue.BGM);
        if (dialogue.Choices.Count > 1)
        {
            GameManager.UI.LoadPopupUI<UISelectDialogue>("SelectPopup").SetVisible(true);
            createLifeEvent.RaiseEvent();
            selectDialogueEvent.RaiseEvent(dialogue);
            return;
        }

        setDialogueEvent.RaiseEvent(dialogue);
    }

    public void InCorrectSelect()
    {
        curLife -= 1;
        //라이프 체크 후 엔딩 실행
        inCorrectSelectEvent.RaiseEvent();
    }

    private void SetBGM(AudioClip bgm)
    {
        if(bgm != null)
        {
            GameManager.Sound.Play(bgm, ESound.BGM);
        }
    }
}
