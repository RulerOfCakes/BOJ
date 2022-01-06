import java.util.*

fun main(args: Array<String>) {
    with(Scanner(System.`in`)) {
        val N = nextInt();
        val adj = Array(N+2){ArrayList<Int>()}
        val tree = Array(N+2){0}
        fun dfs(x:Int,prt:Int, dest:Int, cnt:Int):Boolean{
            if(x==dest){
                tree[x]+=cnt
                return true
            }
            //println("$x wowzers $cnt")
            var ret = false
            for(nx in adj[x]){
                if(nx==prt)continue
                ret=ret||dfs(nx,x,dest,cnt+1);
                if(ret)break
            }
            if(ret)tree[x]+=cnt
            return ret
        }
        for(i in 1 until N){
            val a = nextInt()
            val b = nextInt()
            adj[a].add(b)
            adj[b].add(a)
        }
        //println("red sus")
        val Q = nextInt();
        for (i in 0 until Q) {
            val qType = nextInt()
            if (qType == 1) {
                val a = nextInt()
                val b = nextInt()
                if(!dfs(a,0,b,0))println("wot")
            } else {
                val num = nextInt()
                println(tree[num])
            }
        }
    }
}