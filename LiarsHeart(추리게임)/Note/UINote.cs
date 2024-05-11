using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;

public class UINote : UIScene
{
    [SerializeField] private TMP_InputField noteInputField;
    public TMP_InputField NoteInputField { get => noteInputField; }

    [SerializeField] private Image note;
    [SerializeField] private Button nextPage;
    [SerializeField] private Button prevPage;
    [SerializeField] private TMP_Text pageNum;

    [SerializeField] private List<Button> tabButtonList;

    [SerializeField] private int curPage = 1;

    // BoradCasting
    [SerializeField] private StringEventChannelSO startEditEvent;
    [SerializeField] private StringEventChannelSO endEditEvent;

    // Listening
    [SerializeField] private IntEventChannelSO changePageEvent;
    [SerializeField] private StringEventChannelSO changeNoteEvent;

    const string path = "Events/Note/";

    private void Awake()
    {
        changePageEvent = Resources.Load<IntEventChannelSO>(path + "ChangePageEvent");
        changeNoteEvent = Resources.Load<StringEventChannelSO>(path + "ChangeNoteEvent");
        startEditEvent = Resources.Load<StringEventChannelSO>(path + "StartEditEvent");
        endEditEvent = Resources.Load<StringEventChannelSO>(path + "EndEditEvent");
    }

    private void Start()
    {
        for (int i = 0; i < tabButtonList.Count; i++)
        {
            int noteIndex = i;
            tabButtonList[i].onClick.AddListener(() => NoteManager.Instance.ChangeNote(noteIndex));
            tabButtonList[i].onClick.AddListener(() => ChangeTab(noteIndex));
        }

        nextPage.onClick.AddListener(() => NoteManager.Instance.ChangePage(curPage + 1));
        prevPage.onClick.AddListener(() => NoteManager.Instance.ChangePage(curPage - 1));

        NoteInputField.onSelect.AddListener((value) => startEditEvent.RaiseEvent(value));
        NoteInputField.onEndEdit.AddListener((value) => endEditEvent.RaiseEvent(value));

        ChangeTab(0);
    }

    private void OnEnable()
    {
        changePageEvent.OnEventRaised += SetPageNum;
        changeNoteEvent.OnEventRaised += SetNoteInputField;
    }

    private void OnDisable()
    {
        changePageEvent.OnEventRaised -= SetPageNum;
        changeNoteEvent.OnEventRaised -= SetNoteInputField;
    }

    public void SetNoteInputField(string note)
    {
        noteInputField.text = note;
    }

    public void SetPageNum(int pageNum)
    {
        this.pageNum.text = "-" + pageNum.ToString() + "-";
        curPage = pageNum;
    }

    public void ChangeTab(int idx)
    {
        foreach (Button tab in tabButtonList)
        {
            if(tab == tabButtonList[idx])
            {
                tab.gameObject.GetComponent<Image>().color = new Color32(242, 241, 221, 255);
            }
            else
            {
                tab.gameObject.GetComponent<Image>().color = new Color32(202, 190, 159, 255);
            }
        }
    }
}
