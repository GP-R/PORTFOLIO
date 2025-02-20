using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using DS.ScriptableObjects;
using DS.Data;

public class UIDialogue : UIPopup
{
    [SerializeField] private Image leftLocation;
    [SerializeField] private Image centerLocation;
    [SerializeField] private Image rightLocation;

    [SerializeField] private Image background;

    // Chat Box
    [SerializeField] private TMP_Text nameText;
    [SerializeField] private TMP_Text contentText;

    [SerializeField] private ToggleGroup toggleGroup;
    [SerializeField] private DialogueToggle progressToggle;
    [SerializeField] private DialogueToggle autoProgressToggle;
    [SerializeField] private DialogueToggle fastAutoProgressToggle;

    [SerializeField] private Button dialogueHistoryButton;

    [SerializeField] private bool autoProgress = false;
    [SerializeField] private float delay = 0.05f;
    [SerializeField] private float autoProgressDelay = 1.0f;

    // Listening
    [SerializeField] private DialogueEventChannelSO setDialogueEvent;

    private Coroutine curCoroutine = null;
    private DSDialogueSO curDialogue = null;

    private bool isComplete = false;

    private void OnEnable()
    {
        setDialogueEvent.OnEventRaised += StartDialogueCoroutine;

        progressToggle.Toggle.group = toggleGroup;
        autoProgressToggle.Toggle.group = toggleGroup;
        fastAutoProgressToggle.Toggle.group = toggleGroup;

        progressToggle.Toggle.onValueChanged.AddListener(OnProgressToggle);
        autoProgressToggle.Toggle.onValueChanged.AddListener(OnAutoProgressToggle);
        fastAutoProgressToggle.Toggle.onValueChanged.AddListener(OnFastAutoProgressToggle);

        dialogueHistoryButton.onClick.AddListener(OnClikedDialogueHistoryButton);
    }

    private void OnDisable()
    {
        setDialogueEvent.OnEventRaised -= StartDialogueCoroutine;
        createLifeEvent.OnEventRaised -= CreateLifeImage;
        inCorrectSelectEvent.OnEventRaised -= PlayInCorrectSelectEffect;

        progressToggle.Toggle.onValueChanged.RemoveListener(OnProgressToggle);
        autoProgressToggle.Toggle.onValueChanged.RemoveListener(OnAutoProgressToggle);
        fastAutoProgressToggle.Toggle.onValueChanged.RemoveListener(OnFastAutoProgressToggle);

        dialogueHistoryButton.onClick.RemoveListener(OnClikedDialogueHistoryButton);
    }

    private void Update()
    {
        if(!isComplete)
        {
            if (Input.GetKeyDown(KeyCode.Space))
            {
                isComplete = true;
            }
        }
    }

    private void OnProgressToggle(bool value)
    {
        if (value)
        {
            autoProgress = false;
        }
    }

    private void OnAutoProgressToggle(bool value)
    {
        if(value)
        {
            autoProgress = true;
            delay = 0.05f;
        }
    }

    private void OnFastAutoProgressToggle(bool value)
    {
        if (value)
        {
            autoProgress = true;
            delay = 0.02f;
        }
    }

    private void OnClikedDialogueHistoryButton()
    {
        UIDialoguePopupRecord popupUI = GameManager.UI.LoadPopupUI<UIDialoguePopupRecord>("DialogueRecordPopup");
        popupUI.Init(GameManager.Dialogue.SavedDialogueData);
        popupUI.SetVisible(true);
    }

    // 발화자 설정
    private void SetSpeaker(DSDialogueSO dialogueSO)
    {
        leftLocation.color = new Color32(0, 0, 0, 0);
        centerLocation.color = new Color32(0, 0, 0, 0);
        rightLocation.color = new Color32(0, 0, 0, 0);

        foreach (DSDialogueSpeakerData speaker in dialogueSO.Speaker)
        {
            if(speaker.Character != null)
            {
                Image logcationImage = GetImageByLocation(speaker.Location);
                if(speaker.Character.spriteByEmotion.ContainsKey(speaker.Emotion))
                {
                    logcationImage.sprite = speaker.Character.spriteByEmotion[speaker.Emotion];
                }
                if(speaker.IsSpeaked)
                {
                    logcationImage.color = new Color32(255, 255, 255, 255);
                }
                else
                {
                    logcationImage.color = new Color32(80, 80, 80, 255);
                }
            }
        }
    }

    private void SetNameText(DSDialogueSO dialogueSO)
    {
        nameText.text = "";
        foreach (DSDialogueSpeakerData speaker in dialogueSO.Speaker)
        {
            if(speaker.IsSpeaked && speaker.Character != null)
            {
                nameText.text = speaker.Character.Name;
            }
        }
    }

    private void StartDialogueCoroutine(DSDialogueSO dialogueSO)
    {
        if(curCoroutine != null)
        {
            return;
        }

        SetBackgroundImage(dialogueSO.Background);
        SetNameText(dialogueSO);
        SetSpeaker(dialogueSO);
        curDialogue = dialogueSO;
        curCoroutine = StartCoroutine(Dialogue(dialogueSO));
    }

    private IEnumerator Dialogue(DSDialogueSO dialogueSO)
    {
        isComplete = false;
        SetContentText("", false);

        for (int i = 0; i < dialogueSO.Text.Length; i++)
        {
            if (isComplete)
            {
                SetContentText(dialogueSO.Text, false);
                break;
            }
            PlaySoundEffect(contentText.text.Length);
            SetContentText(dialogueSO.Text[i].ToString(), true);
            yield return new WaitForSeconds(delay);
        }
        yield return new WaitForSeconds(0.2f); // 연타 방지
        yield return new WaitUntil(() => (Input.GetKeyDown(KeyCode.Space)) || autoProgress);
        if (autoProgress)
        {
            yield return new WaitForSeconds(autoProgressDelay);
        }

        curCoroutine = null;
        curDialogue = null;
        GameManager.Dialogue.PlayDialogue(dialogueSO.Choices[0].NextDialogue);
    }

    private void SetContentText(string content, bool isChar)
    {
        if (isChar)
        {
            contentText.text += content;
            return;
        }

        contentText.text = content;
    }

    private Image GetImageByLocation(ELocation location)
    {
        if (location == ELocation.Left)
        {
            return leftLocation;
        }
        else if (location == ELocation.Center)
        {
            return centerLocation;
        }
        else if (location == ELocation.Right)
        {
            return rightLocation;
        }

        return null;
    }

    private void PlaySoundEffect(int length)
    {
        if(!curDialogue.SoundEffects.ContainsKey(length))
        {
            return;
        }
        GameManager.Sound.Play(curDialogue.SoundEffects[length]);
    }

    public void SetBackgroundImage(Sprite background)
    {
        if(background != null)
        {
            this.background.sprite = background;
        }
    }
}
