using System.Collections.Generic;
using UnityEngine;

public class NoteData
{
    [SerializeField] private List<string> notes = new List<string>();
    public List<string> Notes { get => notes; set => notes = value; }
}

public class NoteManager : Singleton<NoteManager>
{
    [SerializeField] private List<NoteData> noteList = new List<NoteData>();

    [SerializeField] private int curNoteIndex = 0;
    [SerializeField] private int noteCount = 3;
    [SerializeField] private bool editMode = false;

    [SerializeField] private int pageLimit = 10;
    [SerializeField] private int curPage = 1;

    // BoradCasting
    [SerializeField] private IntEventChannelSO changePageEvent;
    [SerializeField] private StringEventChannelSO changeNoteEvent;

    // Listening
    [SerializeField] private StringEventChannelSO startEditEvent;
    [SerializeField] private StringEventChannelSO endEditEvent;

    const string path = "Events/Note/";

    protected override void Awake()
    {
        base.Awake();
        changePageEvent = Resources.Load<IntEventChannelSO>(path + "ChangePageEvent");
        changeNoteEvent = Resources.Load<StringEventChannelSO>(path + "ChangeNoteEvent");
        startEditEvent = Resources.Load<StringEventChannelSO>(path + "StartEditEvent");
        endEditEvent = Resources.Load<StringEventChannelSO>(path + "EndEditEvent");
    }

    private void OnEnable()
    {
        startEditEvent.OnEventRaised += OnInputSelected;
        endEditEvent.OnEventRaised += SaveNote;
    }

    private void OnDisable()
    {
        startEditEvent.OnEventRaised -= OnInputSelected;
        endEditEvent.OnEventRaised -= SaveNote;
    }

    private void Start()
    {
        for(int i = 0; i < noteCount; i++)
        {
            NoteData noteData = new NoteData();
            for (int j = 0; j < pageLimit; j++)
            {
                noteData.Notes.Add("");
            }
            noteList.Add(noteData);
        }
    }

    private void Update()
    {
        if(!editMode)
        {
            if(Input.GetKeyDown(KeyCode.N))
            {
                ChangePage(curPage + 1);
            }
            if(Input.GetKeyDown(KeyCode.M))
            {
                ChangePage(curPage - 1);
            }
        }
    }

    public void ChangeNote(int noteIndex)
    {
        curNoteIndex = noteIndex;
        ChangePage(1);

        // TODO: 임시코드
        GameManager.Sound.Play("SFX/SFX_Click_Common");
    }

    public void ChangePage(int pageNum)
    {
        curPage = pageNum;
        if (curPage > pageLimit)
        {
            curPage = 1;
        }
        else if (curPage < 1)
        {
            curPage = pageLimit;
        }
        changePageEvent.RaiseEvent(curPage);
        changeNoteEvent.RaiseEvent(noteList[curNoteIndex].Notes[curPage - 1]);

        // TODO: 임시코드
        GameManager.Sound.Play("SFX/SFX_Click_Common");
    }

    public void SaveNote(string memo)
    {
        Debug.Log("Save Note");
        noteList[curNoteIndex].Notes[curPage - 1] = memo;
        editMode = false;
    }

    public void OnInputSelected(string note)
    {
        editMode = true;
    }
}
