using UnityEngine;
using UnityEngine.UI;
using TMPro;
using DS.ScriptableObjects;
using System.Collections.Generic;
using DS.Data;

public class UIDialoguePopupRecord : UIPopup
{
    [SerializeField] private Transform parent;
    [SerializeField] private GameObject ChatMessagePrefab;

    [SerializeField] Button exitButton;

    private void Start()
    {
        exitButton.onClick.AddListener(() => SetVisible(false));
    }

    public void Init(List<DSDialogueSO> datas)
    {
        for (int i = 0; i < datas.Count; i++)
        {
            UIChatMessage clone = Instantiate(ChatMessagePrefab, parent).GetComponent<UIChatMessage>();
            foreach(DSDialogueSpeakerData speaker in datas[i].Speaker)
            {
                if(speaker.IsSpeaked)
                {
                    CharacterSO tmp = speaker.Character;
                    clone.Init(tmp);
                }
            }

            clone.SetText(datas[i].Text);
        }
    }
}
