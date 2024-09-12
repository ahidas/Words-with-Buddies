import './style.css';

export function loading({percent}){

    return(
        <>
        <div className="bar">
            <div className="filler" style={{width: `${percent}%`}}/>
        </div>
        </>
    )
}